// ITEM Made by player(��������:awsl) /data/item/a/awsl-bzq.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu Jan 17 22:45:07 2019
#include <ansi.h>
#include <armor.h>

inherit PANTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;35m����ȹ[2;37;0m", ({ "bzq" }));
	set_weight(1800);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[33m�ڽ�˿[2;37;0m���ƶ��ɵ�һ�����ӡ�
[1;35mһ��Ư����Сȹ��[2;37;0m
����Ե�Ͽ���һ��С�֣���������(awsl)
");
	set("value", 1500000);
	set("point", 77);
	set("material", "silk");
	set("wear_msg", "����[2;37;0m\n");
	set("remove_msg", "����[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
