// jinbagua.c

inherit ITEM;

void create()
{
	set_name("�����", ({ "jin bagua", "bagua" }));
	set_weight(1200);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("no_sell", "��...����ʲô�������ҿɲ���Ҫ��\n");
		set("long", "һ�洿��ĵ�Ƕ��İ��ԣ��ǳ�����\n");
		set("value", 1);
		set("material", "gold");
	}
	setup();
}
