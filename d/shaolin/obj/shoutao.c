// shoutao.c

#include <ansi.h>
#include <armor.h>

inherit HANDS;

void create()
{
	set_name("Ƥ����", ({ "pi shoutao", "shoutao" }));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "˫");
		set("long", "����һ˫Ƥ���ף�������Ӳ����յĺۼ���\n");
		set("value", 3000);
		set("armor_prop/armor", 1);
		set("armor_prop/hand", 1);
		set("armor_prop/strike", 1);
		set("armor_prop/unarmed_damage", 3);
		set("shaolin",1);
	}
	setup();
}
