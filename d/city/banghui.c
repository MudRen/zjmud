// by ranger_����
// banghui.c

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", "������������ڴˡ�����������Ծۼ�������Ӵ����Լ��İ�ᣬ���һ�𹲴�������");
	set("exits", ([
		"southeast" : __DIR__"guangchang",
	]));

	set("action_list", ([
		HIG"�������"NOR:"banghui create",
	]));
	set("no_fight","1");
	setup();
}

