// ITEM Made by player(��������:awsl) /data/item/a/awsl-www.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jan 13 00:10:48 2019
#include <ansi.h>
#include <armor.h>

inherit BOOTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;37m��˿��[2;37;0m", ({ "www" }));
	set_weight(1080);
	set("item_make", 1);
	set("unit", "˫");
	set("long", "������[33m�ڽ�˿[2;37;0m���ƶ��ɵ�һ˫ѥ�ӡ�
[1;37mһ˫��ϸ������[2;37;0m
ѥ��Ե�Ͽ���һ��С�֣���������(awsl)
");
	set("value", 1500000);
	set("point", 61);
	set("material", "silk");
	set("wear_msg", "����[2;37;0m\n");
	set("remove_msg", "����[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/dodge", apply_armor() / 10 + 1);

	setup();
}

string long() { return query("long") + item_long(); }
