// Room: wuxiuxi.c

inherit ROOM;

void create()
{
	set("short", "��ţ��ݵ�����");
	set("long", @LONG
�����ǡ���ţ��ݡ��ĵ����ң���Ȼ���ݣ���Ҳ���ֻ����Щ�谵��
��ǽ�м����̵ĺúõĴ�����Щ��������Ϣ��������ƣ�뻵�ˡ�
LONG );
	set("no_fight", 1);
	set("sleep_room", 1);
	set("exits", ([
		"up" : __DIR__"wuguan",
	]));
	setup();
}
