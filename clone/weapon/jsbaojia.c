#include <ansi.h>
#include <armor.h>

inherit ARMOR;

void create()
{
	set_name(CYN "��˿" HIY "����" NOR,  ({ "bao jia", "jia", "armor" }));
	set_weight(6000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("icon","05043");
		set("unit", "��");
		set("long", "һ��������ļף��������ۡ�\n");
		set("no_sell", "����������ֵǮô��\n");
		set("value", 100000);
		set("material", "silk");
		set("armor_prop/armor", 200);
		set("stable", 100);
	}

	setup();
	move("/d/beijing/aofu_mishi");
}
