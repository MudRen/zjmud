// ITEM Made by player(������:sxjian) /data/item/s/sxjian-diwang.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Dec 14 21:08:24 2018
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("����ս��[2;37;0m", ({ "diwang" }));
	set_weight(1400);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[1;37m�쾧[2;37;0m���ƶ��ɵ�һ��ս�¡�
ս��Ե�Ͽ���һ��С�֣�������(sxjian)
");
	set("value", 1);
	set("point", 300);
	set("material", "silk");
	set("wear_msg", "[33m$N[33mװ������ս��[2;37;0m[33m��[2;37;0m\n");
	set("remove_msg", "[33m$N[33m�����˵���ս��[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
