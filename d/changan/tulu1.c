// Room:/d/changan/tulu2.c

inherit ROOM;

void create()
{
	set("short", "��·");
	set("long", @LONG
����һ�����������·������̫���ϱ�ԶԶ����ȥ���Կ���
��Ρ��ĳ�����ǽ����Ȼ�����볤������Զ�����Ǿ������ܵ�����
�����������ɧ�ţ�������̲���ïʢ��
LONG);
	set("exits",  ([  /*  sizeof()  ==  2  */
		"northeast": __DIR__"tulu2",
		"south"    : __DIR__"bei-chengmen",
	]));
	set("outdoors", "changan");
	setup();
}
