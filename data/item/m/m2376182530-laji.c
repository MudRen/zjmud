// ITEM Made by player(������:m2376182530) /data/item/m/m2376182530-laji.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Jan  9 13:20:32 2019
#include <ansi.h>
#include <armor.h>

inherit HEAD;
inherit F_ITEMMAKE;

void create()
{
	set_name("����ͷ��[2;37;0m", ({ "laji" }));
	set_weight(3375);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[37m����[2;37;0m���ƶ��ɵ�һ��ͷ����
ͷ��Ե�Ͽ���һ��С�֣�������(m2376182530)
");
	set("value", 700000);
	set("point", 33);
	set("material", "iron");
	set("wear_msg", "[33m$N[33mװ������ͷ��[2;37;0m[33m��[2;37;0m\n");
	set("remove_msg", "[33m$N[33m����������ͷ��[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
