// ITEM Made by player(��������:awsl) /data/item/a/awsl-wsl.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Jan 11 11:00:37 2019
#include <ansi.h>
#include <armor.h>

inherit HEAD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;34mϸ��β�д�[2;37;0m", ({ "wsl" }));
	set_weight(3750);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[37m�Ϲź���[2;37;0m���ƶ��ɵ�һ��ͷ����
[1;34mĳ���Զ���������أ�������Ҫ�����͸��������û������ң�[2;37;0m
ͷ��Ե�Ͽ���һ��С�֣���������(awsl)
");
	set("value", 1500000);
	set("point", 77);
	set("material", "steel");
	set("wear_msg", "ϸ��[2;37;0m\n");
	set("remove_msg", "ȡ��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
