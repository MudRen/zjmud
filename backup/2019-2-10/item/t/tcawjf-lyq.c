// ITEM Made by player(����:tcawjf) /data/item/t/tcawjf-lyq.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Mon Jan 21 17:51:16 2019
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;34m����ȹ[2;37;0m", ({ "lyq" }));
	set_weight(7500);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[37m�Ϲź���[2;37;0m���ƶ��ɵ�һ�Ż��ס�
����Ե�Ͽ���һ��С�֣�����(tcawjf)
");
	set("value", 1500000);
	set("point", 123);
	set("material", "steel");
	set("wear_msg", "[33m$N[33mװ��[1;34m����ȹ[2;37;0m[33m��[2;37;0m\n");
	set("remove_msg", "[33m$N[33m������[1;34m����ȹ[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/parry", apply_armor() / 15 + 1);

	setup();
}

string long() { return query("long") + item_long(); }
