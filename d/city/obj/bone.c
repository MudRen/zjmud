// jitui.c ����

#include <weapon.h>

inherit HAMMER;

void create()
{
	set_name("���ȹ�ͷ", ({ "jitui gu" }));
	set_weight(150);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ���еþ���ļ��ȹ�ͷ��\n");
		set("unit", "��");
		set("wield_msg", "$Nץ��һ��$n���������е�������\n");
		set("material", "bone");
	}
	init_hammer(1);
	setup();
}

