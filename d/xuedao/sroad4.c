// sroad4.c
inherit ROOM;
void create()
{
	set("short", "��ѩɽ��");
	set("long", @LONG
�����Ѿ����˲رߣ���ѩɽ��ɽ�ڡ���ѩɽ�ֽ��ɽ��λ�ڴ�
��֮�䣬����ɽ�Ƹ߾���ɽ�������겻���Ļ�ѩ���ʶ�����������
�����˼���ֻ�м�ֻͺӥ�ڸߴ�������������ããѩɽ��
LONG );
	set("exits", ([
		"eastdown"  : __DIR__"sroad3",
		"westup"    : __DIR__"sroad5",
	]));
	set("objects", ([
		__DIR__"npc/eagle": 2,
	]));
	set("outdoors", "xuedao");
	setup();
}
