// xiangliao.c ����

#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
	set_name("��������", ({ "xiang liao", "xiangliao", "liao" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "����һ�����Ƶ����ϣ���ȼ����Է���Ũ����������\n");
		set("base_unit", "��");
		set("base_weight", 5);
		set("base_value", 1);
		set("no_sell", 1);
		set("unit", "Щ");
	}

	set_amount(1);
	setup();
}

