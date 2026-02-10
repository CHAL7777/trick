#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class BankAccount {
 public:
  BankAccount(std::string owner, std::string account_number, double balance)
      : owner_(std::move(owner)),
        account_number_(std::move(account_number)),
        balance_(balance) {}

  const std::string& owner() const {
    return owner_;
  }

  const std::string& account_number() const {
    return account_number_;
  }

  double balance() const {
    return balance_;
  }

  void deposit(double amount, std::string note = "") {
    if (amount <= 0.0) {
      return;
    }
    apply_transaction("Deposit", amount, std::move(note));
  }

  virtual bool withdraw(double amount, std::string note = "") {
    if (amount <= 0.0 || amount > balance_) {
      return false;
    }
    apply_transaction("Withdraw", -amount, std::move(note));
    return true;
  }

  bool transfer_to(BankAccount& target, double amount, std::string note = "") {
    if (this == &target) {
      return false;
    }
    if (!withdraw(amount, note.empty() ? "Transfer to " + target.account_number()
                                       : "Transfer to " + target.account_number()
                                           + " (" + note + ")")) {
      return false;
    }
    target.deposit(amount, note.empty() ? "Transfer from " + account_number_
                                        : "Transfer from " + account_number_
                                            + " (" + note + ")");
    return true;
  }

  struct Transaction {
    std::string type;
    double amount;
    double balance;
    std::string timestamp;
    std::string note;
  };

  const std::vector<Transaction>& history() const {
    return history_;
  }

 protected:
  static std::string current_timestamp() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    const auto ms_since_epoch =
        std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    const long long millis = ms_since_epoch.count() % 1000;
    std::tm local_time{};
#if defined(_WIN32)
    localtime_s(&local_time, &now_time);
#else
    localtime_r(&now_time, &local_time);
#endif
    std::ostringstream out;
    out << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S")
        << '.' << std::setw(3) << std::setfill('0') << millis;
    return out.str();
  }

  void apply_transaction(std::string type, double delta, std::string note) {
    balance_ += delta;
    history_.push_back(
        Transaction{std::move(type), delta, balance_, current_timestamp(), std::move(note)});
  }

 private:
  std::string owner_;
  std::string account_number_;
  double balance_;
  std::vector<Transaction> history_;
};

class SavingsAccount final : public BankAccount {
 public:
  SavingsAccount(std::string owner,
                 std::string account_number,
                 double balance,
                 double interest_rate)
      : BankAccount(std::move(owner), std::move(account_number), balance),
        interest_rate_(interest_rate) {}

  void apply_interest() {
    if (interest_rate_ <= 0.0) {
      return;
    }
    const double interest = balance() * interest_rate_;
    deposit(interest, "Interest");
  }

 private:
  double interest_rate_;
};

class CheckingAccount final : public BankAccount {
 public:
  CheckingAccount(std::string owner,
                  std::string account_number,
                  double balance,
                  double overdraft_limit)
      : BankAccount(std::move(owner), std::move(account_number), balance),
        overdraft_limit_(overdraft_limit) {}

  bool withdraw(double amount, std::string note = "") override {
    if (amount <= 0.0 || amount > balance() + overdraft_limit_) {
      return false;
    }
    if (note.empty() && amount > balance()) {
      note = "Overdraft";
    }
    apply_transaction("Withdraw", -amount, std::move(note));
    return true;
  }

 private:
  double overdraft_limit_;
};

int main() {
  SavingsAccount savings("Amina Issa", "SA-0142", 1200.0, 0.03);
  CheckingAccount checking("Daniel Reed", "CA-7765", 500.0, 200.0);

  savings.deposit(300.0, "Paycheck");
  savings.apply_interest();
  savings.withdraw(150.0, "Groceries");

  checking.deposit(250.0, "Side job");
  checking.withdraw(800.0, "Rent");

  checking.transfer_to(savings, 200.0, "Monthly savings");

  std::cout << savings.owner() << " (" << savings.account_number()
            << ") balance: " << savings.balance() << '\n';
  std::cout << checking.owner() << " (" << checking.account_number()
            << ") balance: " << checking.balance() << '\n';

  auto print_history = [](const BankAccount& account) {
    std::cout << "\nTransaction history for " << account.owner()
              << " (" << account.account_number() << ")\n";
    for (const auto& entry : account.history()) {
      std::cout << "  [" << entry.timestamp << "] "
                << entry.type << " "
                << entry.amount << " -> balance "
                << entry.balance;
      if (!entry.note.empty()) {
        std::cout << " (" << entry.note << ")";
      }
      std::cout << '\n';
    }
  };

  print_history(savings);
  print_history(checking);

  return 0;
}
