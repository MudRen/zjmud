// nfeecard.c ������ѿ�
//
// ʹ����ѿ���������Ҫ�����κ�����

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIY "��ѿ�" NOR, ({ "card", "fee free card" }));
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ������ס����ѿ���ƾ���ſ��������"
			    "�����κ�ס����\n");
		set("material", "paper");
		set("fee free", 2000000000);
		set("value", 1);
		set("no_sell", 1);
	}
}

int query_autoload() { return 1; }
