pragma solidity>=0.4.24 <0.6.11;

contract syj {
	struct Bill {
		string From;
		string To;
		int Type;
		int Money;
		uint CreateDate;
		uint RepayDate;
	}

	struct Organization {
		string Name;
		int Money;
		int Type;
	}

	int LenOrg;
	int LenBill;
	mapping(string => Organization) Organizations;
	mapping(int => Bill) Bills;

	constructor() public {
		LenOrg = 0;
		LenBill = 0;
	}

	function isEqual(string s1, string s2) public returns(bool) {
		if (bytes(s1).length != bytes(s2).length) return false;
		for (uint i=0; i<bytes(s1).length; i++) {
			if (bytes(s1)[i] != bytes(s2)[i]) return false;
		}
		return true;
	}

	function NewBill(string From, string To, int Money) public returns(int) {
		if (Organizations[From].Type == 1 && Organizations[To].Type == 1 && !isEqual(From, To)) {
			Bills[LenBill++] = Bill(From, To, 1, Money, now, now + 60*1000);
			return LenBill-1;
		}
		return -1;
	}

	function TransferCount(string From, string To) public returns(int) {
		int sum = 0;
		if (Organizations[From].Type == 1 && Organizations[To].Type == 1 && !isEqual(From, To)) {
			for (int i=0; i<LenBill; i++) {
				if (isEqual(Bills[i].To, From) && !isEqual(Bills[i].From, To) && (Bills[i].Type == 1 || Bills[i].Type == 2)) {
					sum += Bills[i].Money;
				}
			}
			return sum;
		}
		return -1;
	}

	function Transfer(string From, string To, int Money) public returns(int) {
		int sum = Money;
		if (TransferCount(From, To) >= Money) {
			for (int i=0; i<LenBill; i++) {
				if (isEqual(Bills[i].To, From) && (Bills[i].Type == 1 || Bills[i].Type == 2)) {
					if (Bills[i].Money > sum) {
						Bills[i].Money -= sum;
						Bills[LenBill++] = Bill(Bills[i].From, To, 2, sum, Bills[i].CreateDate, Bills[i].RepayDate);
						sum = 0;
					}
					else if (!isEqual(Bills[i].From, To)) {
						Bills[i].To = To;
						Bills[i].Type = 2;
						sum -= Bills[i].Money;
					}
					if (sum == 0) break;
				}
			}
			return 0;
		}
		return -1;
	}

	function Raise(string From, string To) public returns(int) {
		int sum = 0;
		if (Organizations[From].Type == 1 && Organizations[To].Type == 0) {
			for (int i=0; i<LenBill; i++) {
				if (isEqual(Bills[i].To, From) && (Bills[i].Type == 1 || Bills[i].Type == 2)) {
					Bills[i].To = To;
					Bills[i].Type = 3;
					sum += Bills[i].Money;
				}
			}
			Organizations[From].Money += sum;
			Organizations[To].Money -= sum;
			return sum;
		}
		return -1;
	}

	function RepayCount(string From) public returns(int) {
		int sum = 0;
		if (Organizations[From].Type == 1) {
			for (int i=0; i<LenBill; i++) {
				if (isEqual(Bills[i].From, From) && Bills[i].Type != 0 && now >= Bills[i].RepayDate) {
					sum += Bills[i].Money;
				}
			}
			return sum;
		}
		return -1;
	}

	function Repay(string From) public returns(int) {
		int sum = 0;
		if (RepayCount(From) != -1 && RepayCount(From) <= Organizations[From].Money) {
			for (int i=0; i<LenBill; i++) {
				if (isEqual(Bills[i].From, From) && Bills[i].Type != 0 && now >= Bills[i].RepayDate) {
					Bills[i].Type = 0;
					sum += Bills[i].Money;
				}
			}
			Organizations[From].Money -= sum;
			return sum;
		}
		return -1;
	}

	function Register(string memory Name, int Money, int Type) public{
		Organizations[Name] = Organization(Name, Money, Type);
		LenOrg++;
	}

	function GetCompany(string memory Name) public view returns(string memory, int, int) {
		return (Organizations[Name].Name, Organizations[Name].Money, Organizations[Name].Type);
	}

	function GetBill(int id) public view returns(string memory, string memory, int, int, uint, uint) {
		return (Bills[id].From, Bills[id].To, Bills[id].Type, Bills[id].Money, Bills[id].CreateDate, Bills[id].RepayDate);
	}
}
