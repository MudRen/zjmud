// Room: /d/xiangyang/qianzhuang.c
inherit ROOM;
void create()
{
	set("short", "Ǯׯ");
	set("long", @LONG
������������Ǯׯ����Ϊ������ҵ�൱������ص��̺�
������������Ǯ������Ǯׯ���кܶ����ڴ�ȡǮ��Ҳ�����ڶ�
��������������ô���Ǯ�ƹ�����ȥ�����������۲���������
�´�е�ǰ��ȫ��һ�µ���Ԫ����Ǯׯ��ҵ���ɻ�ɽ���ӽӹܣ�
֧Ԯ���������͹����ˡ�ǽ������һ�����ӡ�
LONG );
	set("item_desc", ([
		"�����ӡ�" : "��Ǯׯ�ṩ���·���\n"
		ZJOBACTS2+ZJMENUF(3,3,8,30)"��Ǯ:cun"ZJSEP"ȡǮ:qu"ZJSEP"����:check\n",
	]) );
	set("exits", ([
		"east" : __DIR__"southjie1",
	]));
	set("objects", ([
		__DIR__"npc/huangzhen" : 1,
	]));
	setup();
}

