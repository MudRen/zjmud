//      dadian.c ���
inherit ROOM;
void create()
{
	set("short", "���");
	set("long", @LONG
������ѩɽ�µĴ����빩���ŷ�������ɮ����
�����ž��ġ�Զ����������������ϵ�Ĥ�ݡ��������
���ǲ�
LONG );
	set("exits", ([
		"east"  : __DIR__"cedian1",
		"west"  : __DIR__"cedian2",
		"south" : __DIR__"guangchang",
	]));
	set("objects", ([
		CLASS_D("xueshan")+"/lazhang" : 1,
		__DIR__"npc/xiang-ke" : 2,
	]));
	set("valid_startroom", 1);
	setup();
}
