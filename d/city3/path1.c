// Room: path1.c
inherit ROOM;
string look_gaoshi();
void create()
{
	set("short", "佻�Ϫ");
	set("long", @LONG
������佻�Ϫ����С·�ϣ�佻�Ϫˮ��Ө��͸����������ԶԶ
�����ŵ�ˮ�������㡣���˯��ɢ����Ϫ��������ˮ��Ʈ����������
��Ƽ����Ƽ���в����޺��������ȥ��Ϫ��С·��Ϫ���������ƣ�
����û�㣬��Ʈ�ƺ���ʹ�˲�������������ν "���д���" ���ϲ�
���ۡ�
LONG );
	set("outdoors", "chengdu");
	set("exits", ([
		"north"  : __DIR__"path2",
		"east"   : __DIR__"nanheqiaow",
	]));
	set("no_clean_up", 0);
	setup();
}
