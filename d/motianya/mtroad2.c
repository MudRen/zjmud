// mtroad2.c  ����

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
������ï�ܵ�ɭ�֡����ܶ���������ĳ��ݣ�һ����ɭ�ֲ�����
�ա�Զ����ʱ����Ұ�޵ĺ��У���ʵ�ڲ��������������
LONG );
	set("outdoors", "motianya");
	set("exits", ([
	    "east"  : __DIR__"mtroad1",
	    "west"  : __FILE__,
	    "south" : __FILE__,
	    "north" : __DIR__"mtroad3",
	]));

	setup();
}
