//teapot.c

inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name("���", ({ "tea pot", "pot" }));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else 
	{
		set("long", "һ��������Ĳ�������װ�ü���ˮ��\n");
		set("unit", "��");
		set("value", 30);
		set("max_liquid", 10);
	}
	set("liquid", ([
		"name": "��ˮ",
		"remaining": 10,
	]));
}