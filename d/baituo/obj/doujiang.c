// ����

inherit ITEM;
inherit F_LIQUID;

void init();

void create()
{
	set_name("����",({ "cup", "beizi" }));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ���ű��ӡ�\n");
		set("unit", "��");
    	}
	
	set("liquid", ([
		"name": "����",
		"remaining": 7,
	]));
	setup();
}

