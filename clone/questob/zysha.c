// zysha.c

inherit ITEM;

void create()
{
	set_name("����ɴ", ({ "ziyun sha", "sha", "silk" }));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "ƥ");
		set("long", "����һƥ����ɫ�Ļ���˿�񣬱��ü���͸����\n");
		set("value", 5000);
		set("material", "silk");
	}
	setup();
}
