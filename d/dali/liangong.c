// liangong.c

inherit ROOM;

void create()
{
	set("short", "���䳡");
	set("long", @LONG
������һ����̫��Ժ�ӣ��Ƕ����书�ĵط����μ���Ȼ�������壬
���Ǻͽ���ȴ���Ÿ�ϵ���ϵ����˶μ�����������������֣���
��������������ĳ��ء����Ͼ���������Ժ��������ͨ����һ������
����
LONG );
	set("exits", ([
		"north" : __DIR__"liangong2",
		"southeast" : __DIR__"yongdao1",
	]));
	set("objects", ([
		"/clone/npc/mu-ren": 4,
	]));
	set("for_family", "���ϻ���");
	setup();
}
