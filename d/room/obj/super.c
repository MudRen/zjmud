// sfeecard.c ������ѿ�
//
// ʹ����ѿ���������Ҫ�����κ�����

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIC "��ѿ�" NOR, ({ "card", "fee free card" }));
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("material", "paper");
		set("fee free", 200000000);
		set("value", 1);
		set("no_sell", 1);
	}
}

string long()
{
	string msg;

	msg = "����һ�ų���ס����ѿ���ƾ���ſ�������ѹ���һ�׼۸�";
	msg += MONEY_D->price_str(query("fee free"));
	msg += "���µ�ס��һ�ס�\n";
	return msg;
}

int query_autoload() { return 1; }
