// Room: /d/quanzhou/jiaxing.c
inherit ROOM;

void create()
{
	set("short", "���˳�");
	set("long", @LONG
�����ǽ������Ǽ��ˡ��Ƕ��Ƿ羰�续���Ϻ����Ǳ�������������¥��
����ȫ������֮һ���𴦻��ͽ����߹־���������ԼѰ������֮�󡣲�֪
��ʲôԭ���������Ǩ�������ˡ�
LONG );
	set("exits", ([
		"west" : __DIR__"qzroad2",
		"east" : __DIR__"nanhu",
		"south" : __DIR__"jxnanmen",
	]));
	set("outdoors", "jiaxing");
	setup();
}
