// yunshang.c

#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
	set_name(HIG "����" NOR, ({ "yunshang" }));
	set("long", "����һ��֯Ů�ü�����֮��֯�ɵ����ѡ�\n");
	set_weight(10);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("material", "cloth");
		set("unit", "��");
		set("value", 1);
		set("armor_prop/armor", 1);
	}
	setup();
}
