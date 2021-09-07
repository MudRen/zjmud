// wineskin.c  �ƴ�

inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name("ţƤ�ƴ�", ({"jiudai", "wineskin", "skin"}));
	set_weight(700);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ������װ�׾ƵĴ�ƴ������װ�ðˡ������ľơ�\n");
		set("unit", "��");
		set("value", 1500);
		set("max_liquid", 1000);
	}

	// because a container can contain different liquid
	// we set it to contain wine at the beginning
	set("liquid", ([
//		"type": "alcohol",
		"type": "water",
		"name": "�׾�",
		"remaining": 1000,
		"drunk_apply": 100,
	]));
}
