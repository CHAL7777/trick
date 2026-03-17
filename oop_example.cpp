#include <iostream>
#include <string>
#include <utility>

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

  void deposit(double amount) {
    if (amount <= 0.0) {
      return;
    }
    balance_ += amount;
  }

  bool withdraw(double amount) {
    if (amount <= 0.0 || amount > balance_) {
      return false;
    }
    balance_ -= amount;
    return true;
  }

 private:
  std::string owner_;
  std::string account_number_;
  double balance_;
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
    deposit(interest);
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

  bool withdraw(double amount) {
    if (amount <= 0.0 || amount > balance() + overdraft_limit_) {
      return false;
    }
    deposit(-amount);
    return true;
  }

 private:
  double overdraft_limit_;
};

int main() {
  SavingsAccount savings("Amina Issa", "SA-0142", 1200.0, 0.03);
  CheckingAccount checking("Daniel Reed", "CA-7765", 500.0, 200.0);

  savings.deposit(300.0);
  savings.apply_interest();
  savings.withdraw(150.0);

  checking.deposit(250.0);
  checking.withdraw(800.0);

  std::cout << savings.owner() << " (" << savings.account_number()
            << ") balance: " << savings.balance() << '\n';
  std::cout << checking.owner() << " (" << checking.account_number()
            << ") balance: " << checking.balance() << '\n';

  return 0;
}
