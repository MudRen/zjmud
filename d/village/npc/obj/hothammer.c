// hammer.c

#include <weapon.h>

inherit HAMMER;

void create()
{
	set_name("�պ������", ({ "hot hammer" }) );
	set_weight(8000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�����ص�������������൱��ʵ��\n");
		set("value", 300);
		set("material", "iron");
		set("wield_msg", "$N�ó�һ��$n��������������Ȼ���������С�\n");
		set("unwield_msg", "$N�������е�$n��\n");
		set("stable", 0);
	}

	init_hammer(45);
	setup();
}