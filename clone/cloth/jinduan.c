// jinduan.c

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
	set_name(HIY "����" NOR, ({ "jinduan", "jin" }));
	set("long", "����һ��װ�������Ľ��С�\n");
	set_weight(10);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("material", "cloth");
		set("unit", "��");
		set("armor_prop/armor", 1);
		set("value", 1);
	}
	setup();
}
