// ITEM Made by player(����:q456789) /data/item/q/q456789-kuzi.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu Jan 31 11:55:34 2019
#include <ansi.h>
#include <armor.h>

inherit PANTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;36m�¶�����[2;37;0m", ({ "kuzi" }));
	set_weight(700);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[1;37m�쾧[2;37;0m���ƶ��ɵ�һ�����ӡ�
����Ե�Ͽ���һ��С�֣�����(q456789)
");
	set("value", 6100000);
	set("point", 330);
	set("material", "silk");
	set("wear_msg", "[33m$N[33mװ��[1;36m�¶�����[2;37;0m[33m��[2;37;0m\n");
	set("remove_msg", "[33m$N[33m������[1;36m�¶�����[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
