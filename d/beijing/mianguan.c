inherit ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
�����ǻ���·��ͷ��һ��С��ݣ������ʹ����ˤ����ӵ�����档��ݵ�
�ƹ�ͻ���������ǵ���ͷ��������Ҳ���ҳ�һ����
LONG );
	set("exits", ([
		"north" : __DIR__"fu_1",
	]));
	set("objects", ([
		__DIR__"npc/zhanggui":1,
		__DIR__"npc/mianhuoji":1,
		__DIR__"npc/jiao1":3,
		__DIR__"npc/jiao2":1,
	]));
	setup();
}

