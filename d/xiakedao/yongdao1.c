// yongdao1.c ��


inherit ROOM;

void create()
{
	set("short", "��");
	set("long", @LONG
����һ���������������ߵ����͵ƣ������䰵��ȴҲ�ɱ��
·��������Լ�������ٲ���¡¡ˮ��������ˮ���ɽ�����������ʪ��
LONG );
	set("exits", ([
	       "south" : __DIR__"yongdao2",
	       "north" : __DIR__"pubu",
	]));
	setup();
}
