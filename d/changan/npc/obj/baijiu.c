//baijiu.c

inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name("���Ӿ�ƿ", ({"jiuping", "skin"}));
	set_weight(800);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "һ������װ�Ƶľ�ƿ����װ��������׾ơ�\n");
		set("unit", "��");
		set("value", 100);
		set("max_liquid", 15);
	}
	set("liquid", ([
		"type": "alcohol",
		"name": "���ʰ׾�",
		"remaining": 15,
		"drunk_supply": 15,
	]));
}