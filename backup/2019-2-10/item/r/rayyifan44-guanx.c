// ITEM Made by player(����:rayyifan44) /data/item/r/rayyifan44-guanx.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Mon Jan  7 15:23:23 2019
#include <ansi.h>
#include <armor.h>

inherit BOOTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("��ѥ[2;37;0m", ({ "guanx" }));
	set_weight(3000);
	set("item_make", 1);
	set("unit", "˫");
	set("long", "������[37m�Ϲź���[2;37;0m���ƶ��ɵ�һ˫ѥ�ӡ�
ѥ��Ե�Ͽ���һ��С�֣�����(rayyifan44)
");
	set("value", 1500000);
	set("point", 61);
	set("material", "steel");
	set("wear_msg", "[33m$N[33mװ����ѥ[2;37;0m[33m��[2;37;0m\n");
	set("remove_msg", "[33m$N[33m�����˹�ѥ[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/dodge", apply_armor() / 10 + 1);

	setup();
}

string long() { return query("long") + item_long(); }
