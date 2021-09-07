// axe.c

#include <weapon.h>

inherit AXE;

void create()
{
	set_name("��ͷ", ({ "axe", "fu tou" }));
	set_weight(10000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�Ѹ�ͷ����Ϊ���أ��Ƿ����ĺù��ߡ�\n");
		set("value", 1000);
		set("material", "steel");
		set("wield_msg", "$Nץ��һ�Ѹ�ͷ���������С�\n");
		set("unwield_msg", "$N�����еĸ�ͷ���˻�����\n");
	}
	init_axe(30, TWO_HANDED);
	setup();
}
