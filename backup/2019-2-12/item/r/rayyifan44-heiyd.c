// ITEM Made by player(�ɺ�:rayyifan44) /data/item/r/rayyifan44-heiyd.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan 15 11:08:55 2019
#include <ansi.h>
#include <armor.h>

inherit WAIST;
inherit F_ITEMMAKE;

void create()
{
	set_name("������[2;37;0m", ({ "heiyd" }));
	set_weight(1440);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[33m�ڽ�˿[2;37;0m���ƶ��ɵ�һ��������
����Ե�Ͽ���һ��С�֣��ɺ�(rayyifan44)
");
	set("value", 1500000);
	set("point", 61);
	set("material", "silk");
	set("wear_msg", "[33m$N[33mװ��������[2;37;0m[33m��[2;37;0m\n");
	set("remove_msg", "[33m$N[33m�����˺�����[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
