// ITEM Made by player(������:sj2605673550) /data/item/s/sj2605673550-qwe.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sat Jan  5 16:38:52 2019
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;31mս��[2;37;0m", ({ "qwe" }));
	set_weight(3600);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[33m�ڽ�˿[2;37;0m���ƶ��ɵ�һ��ս�¡�
ս��Ե�Ͽ���һ��С�֣�������(sj2605673550)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "silk");
	set("wear_msg", "[33m$N[33mװ��[1;31mս��[2;37;0m[33m��[2;37;0m\n");
	set("remove_msg", "[33m$N[33m������[1;31mս��[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
