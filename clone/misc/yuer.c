// yuer.c ���

#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
	set_name("���", ({ "yu er", "er" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "���ǵ����߳��õ���ʳ��\n");
		set("base_unit", "��");
		set("base_weight", 30);
		set("base_value", 7);
		set("no_sell", "����ԵĶ�����Ҳ���ң�");
		set("unit", "Щ");
	}

	set_amount(1);
	setup();
}

