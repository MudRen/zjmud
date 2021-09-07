// pigdie.c

inherit ITEM;
inherit F_CUTABLE;

void create()
{
	set_name("����", ({ "pig", "pigdie" }));
	set_weight(50000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("parts", ([
			"zhutou" : ({ 0, "��", "��ͷ", "��ͷ", "zhutou",
				      0, "����", __DIR__"zhutou" }),
			"forleg" : ({ 0, "��", "ǰ��", "ǰ��", "forleg",
				      0, "����", __DIR__"forleg" }),
			"backleg": ({ 0, "��", "����", "����", "backleg",
				      0, "����", __DIR__"backleg" }),
		]));
		set("long", "����һֻ��ȥ��Ұ��������Ϊ��׳���������Ը���Ⳣ����\n");
		set("unit", "ֻ");
		set("value", 1000);
	};

	setup();
}

string long() { return ::long() + extra_desc(); }
