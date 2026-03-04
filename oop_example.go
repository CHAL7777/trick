package main

import (
	"fmt"
	"time"
)

// Transaction represents a single transaction
type Transaction struct {
	Type     string
	Amount   float64
	Balance  float64
	Timestamp string
	Note     string
}

// BankAccount interface for polymorphism
type BankAccount interface {
	Deposit(amount float64, note string)
	Withdraw(amount float64, note string) bool
	TransferTo(target BankAccount, amount float64, note string) bool
	Owner() string
	AccountNumber() string
	Balance() float64
	History() []Transaction
}

// bankAccountBase provides common functionality
type bankAccountBase struct {
	owner         string
	accountNumber string
	balance       float64
	history       []Transaction
}

func (b *bankAccountBase) Owner() string {
	return b.owner
}

func (b *bankAccountBase) AccountNumber() string {
	return b.accountNumber
}

func (b *bankAccountBase) Balance() float64 {
	return b.balance
}

func (b *bankAccountBase) History() []Transaction {
	return b.history
}

func (b *bankAccountBase) applyTransaction(typ string, delta float64, note string) {
	b.balance += delta
	b.history = append(b.history, Transaction{
		Type:      typ,
		Amount:    delta,
		Balance:   b.balance,
		Timestamp: time.Now().Format("2006-01-02 15:04:05.000"),
		Note:      note,
	})
}

// BankAccountImpl is a concrete BankAccount
type BankAccountImpl struct {
	bankAccountBase
}

func NewBankAccount(owner, accountNumber string, balance float64) BankAccount {
	return &BankAccountImpl{
		bankAccountBase: bankAccountBase{
			owner:         owner,
			accountNumber: accountNumber,
			balance:       balance,
		},
	}
}

func (b *BankAccountImpl) Deposit(amount float64, note string) {
	if amount <= 0 {
		return
	}
	b.applyTransaction("Deposit", amount, note)
}

func (b *BankAccountImpl) Withdraw(amount float64, note string) bool {
	if amount <= 0 || amount > b.balance {
		return false
	}
	b.applyTransaction("Withdraw", -amount, note)
	return true
}

func (b *BankAccountImpl) TransferTo(target BankAccount, amount float64, note string) bool {
	if _, ok := target.(*BankAccountImpl); !ok {
		return false // Simplified check; in real code, handle any BankAccount
	}
	tImpl := target.(*BankAccountImpl)
	if b == tImpl {
		return false
	}
	if !b.Withdraw(amount, note) {
		return false
	}
	tImpl.Deposit(amount, note)
	return true
}

// SavingsAccount embeds BankAccountImpl and adds interest
type SavingsAccount struct {
	*BankAccountImpl
	interestRate float64
}

func NewSavingsAccount(owner, accountNumber string, balance, interestRate float64) *SavingsAccount {
	ba := NewBankAccount(owner, accountNumber, balance).(*BankAccountImpl)
	return &SavingsAccount{
		BankAccountImpl: ba,
		interestRate:    interestRate,
	}
}

func (s *SavingsAccount) ApplyInterest() {
	if s.interestRate <= 0 {
		return
	}
	interest := s.Balance() * s.interestRate
	s.Deposit(interest, "Interest")
}

// CheckingAccount embeds and overrides Withdraw for overdraft
type CheckingAccount struct {
	*BankAccountImpl
	overdraftLimit float64
}

func NewCheckingAccount(owner, accountNumber string, balance, overdraftLimit float64) *CheckingAccount {
	ba := NewBankAccount(owner, accountNumber, balance).(*BankAccountImpl)
	return &CheckingAccount{
		BankAccountImpl: ba,
		overdraftLimit:  overdraftLimit,
	}
}

func (c *CheckingAccount) Withdraw(amount float64, note string) bool {
	if amount <= 0 || amount > c.Balance()+c.overdraftLimit {
		return false
	}
	if amount > c.Balance() && note == "" {
		note = "Overdraft"
	}
	c.BankAccountImpl.applyTransaction("Withdraw", -amount, note)
	return true
}

func printHistory(account BankAccount) {
	fmt.Printf("\nTransaction history for %s (%s)\n", account.Owner(), account.AccountNumber())
	for _, entry := range account.History() {
		fmt.Printf("  [%s] %s %.2f -> balance %.2f", entry.Timestamp, entry.Type, entry.Amount, entry.Balance)
		if entry.Note != "" {
			fmt.Printf(" (%s)", entry.Note)
		}
		fmt.Println()
	}
}

func main() {
	savings := NewSavingsAccount("Amina Issa", "SA-0142", 1200.0, 0.03)
	savings.Deposit(300.0, "Paycheck")
	savings.ApplyInterest()
	savings.Withdraw(150.0, "Groceries")

	checking := NewCheckingAccount("Daniel Reed", "CA-7765", 500.0, 200.0)
	checking.Deposit(250.0, "Side job")
	checking.Withdraw(800.0, "Rent")

	checking.TransferTo(savings, 200.0, "Monthly savings")

	fmt.Printf("%s (%s) balance: %.2f\n", savings.Owner(), savings.AccountNumber(), savings.Balance())
	fmt.Printf("%s (%s) balance: %.2f\n", checking.Owner(), checking.AccountNumber(), checking.Balance())

	printHistory(savings)
	printHistory(checking)
}
