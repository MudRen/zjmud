// jingua.c

inherit ITEM;

void create()
{
	set_name("���", ({ "jin gua", "gua" }));
	set_weight(8000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һֻ��ͭ�����Ķƽ��״��͸¶��һ�ɻ�����Ϣ��\n");
		set("value", 5000);
		set("material", "copper");
	}
	setup();
}
