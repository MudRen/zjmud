// ITEM Made by player(��������:awsl) /data/item/a/awsl-dqy.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jan 13 10:31:12 2019
#include <ansi.h>
#include <armor.h>

inherit WAIST;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[35mС�ɵĶ�����[2;37;0m", ({ "dqy" }));
	set_weight(1440);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[33m�ڽ�˿[2;37;0m���ƶ��ɵ�һ��������
[35mС�ɵĶ�����[2;37;0m
����Ե�Ͽ���һ��С�֣���������(awsl)
");
	set("value", 1500000);
	set("point", 61);
	set("material", "silk");
	set("wear_msg", "��������[2;37;0m\n");
	set("remove_msg", "ȡ������[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
