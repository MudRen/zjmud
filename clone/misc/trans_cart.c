// trans_cart.c
//

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("��", ({ "cart" }));
	set_weight(200000);
	set_max_encumbrance(1000000);
	if (clonep())
	{
		set_default_object(__FILE__);
		call_out("destruct_me", 10);
	}
	else
	{
		set("value", 1);
		set("long", "����һ����ͨ��������ʻ�ڴ�ٵ��ϣ�����ûλ����Ƶġ�\n");
		set("unit", "��");
		set("material", "wood");
		set("no_get", "�üһ����Ҳ�뿸�ڼ��ϣ�\n");
	}
	setup();
}

void destruct_me()
{
	destruct(this_object());
}
