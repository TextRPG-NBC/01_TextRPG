#include "Shop.h"
#include "Character.h"
#include <iostream>

Shop::Shop() {
	stock.push_back(std::make_unique<HP_Potion>());
	stock.push_back(std::make_unique<AtkBoost>());
}

void Shop::ShowItems() const {
	std::cout << "\n[상점 목록]\n";
	for (size_t i = 0; i < stock.size(); ++i) {
		std::cout << i + 1 << ". " << stock[i]->GetName() << " - 가격: " << stock[i]->GetPrice() << " 골드\n";
	}
}

void Shop::Buy(Player& p) {
	ShowItems();
	std::cout << "구매할 아이템 번호(0: 취소): ";
	int sel;
	std::cin >> sel;
	if (sel <= 0 || (size_t)sel > stock.size()) return;
	int price = stock[sel - 1]->GetPrice();
	if (p.GetGold() < price) {
		std::cout << "[상점] 골드가 부족합니다.\n";
		return;
	}
	p.SpendGold(price);
	// 새 객체로 추가
	if (stock[sel - 1]->GetName() == "HP포션") {
		p.AddItem(std::make_unique<HP_Potion>());
	}
	else if (stock[sel - 1]->GetName() == "공격력부스트") {
		p.AddItem(std::make_unique<AtkBoost>());
	}
	std::cout << "[상점] 구매 완료!\n";
}

void Shop::Sell(Player& p) {
	auto& inv = p.GetInventory();
	if (inv.empty()) {
		std::cout << "[상점] 판매할 아이템이 없습니다.\n";
		return;
	}
	std::cout << "[보유 아이템]\n";
	for (size_t i = 0; i < inv.size(); ++i) {
		std::cout << i + 1 << ". " << inv[i]->GetName() << " (판매가: " << inv[i]->GetPrice() * 0.6 << " 골드)\n";
	}
	std::cout << "판매할 번호(0: 취소): ";
	int sel;
	std::cin >> sel;
	if (sel <= 0 || (size_t)sel > inv.size()) return;
	int price = inv[sel - 1]->GetPrice();
	p.AddGold(static_cast<int>(price * 0.6));
	p.RemoveItemByIdx(sel - 1);
	std::cout << "[상점] 판매 완료!\n";
}
