// ITEM Made by player(����:sun1903) /data/item/s/sun1903-qwer.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Jan  2 16:15:52 2019
#include <ansi.h>
#include <armor.h>

inherit BOOTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[33m����[2;37;0m", ({ "qwer" }));
	set_weight(1080);
	set("item_make", 1);
	set("unit", "˫");
	set("long", "������[33m�ڽ�˿[2;37;0m���ƶ��ɵ�һ˫ѥ�ӡ�
[1;33m���ڻ�ɫ�������ϣ����������Ϣ��ѥ�ӣ��������������ǵĽ���[2;37;0m
ѥ��Ե�Ͽ���һ��С�֣�����(sun1903)
");
	set("value", 1500000);
	set("point", 61);
	set("material", "silk");
	set("wear_msg", "[33m$N[33mװ��[2;37;0m[33m����[2;37;0m[33m��[2;37;0m\n");
	set("remove_msg", "[33m$N[33m������[2;37;0m[33m����[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/dodge", apply_armor() / 10 + 1);

	setup();
}

string long() { return query("long") + item_long(); }
