inherit ROOM;

void create()
{
	set("short", "����ϷԺ");
	set("long", @LONG
������Ǿ����������ĳ���ϷԺ���Ǿ��ǰ�����Ϣ�����ֵļ�����Ϸ̨��
�漸��Ϸ�����ڳ�Ϸ��̨�º�ѹѹ��һƬ�����ˡ��������̨�µĹ����ǽ�
��ס�����Ȳɡ�����һ��С��ͨ��ϷԺ�ĺ�̨��
LONG );
	set("exits", ([
		"north" : __DIR__"xiyuanup",
		"west"   : __DIR__"wang_10",
	]));
	set("objects", ([
		__DIR__"npc/guanzhong" : 3,
		__DIR__"npc/xianren" : 1,
		__DIR__"npc/jumin1" : 1,
	]));

	setup();
}

