// guandao1.c �ٵ�
// By Lgg,1998.10

inherit ROOM;

void create()
{
	set("short", "�ٵ�");
	set("long", @LONG
����һ�����������ͨ���书�򣬶��������ǳ����ǡ����ϵ�
���˺ܶ࣬����ǵ���ͷ�Լ����Լ���·����Ȼ�������������
�õ�����������һ�������ƥ���������߷ɳ۶�����������һƬ
��ɳ��
LONG
	);
	set("outdoors", "wugong");
	set("exits", ([
		"west" : __DIR__"guandao2",
		"northeast": "/d/changan/nan-chengmen",
	]));
	setup();
}

