inherit ROOM;

void create()
{
	set("short", "����Ժ");
	set("long", @LONG
��һ�߽�����һ�۾Ϳ���������ǽ�Ϲ���һ��������ͼ��һ���Ӿ�������
����ʲô�ط������ڵ����ŵƽ�ʣ������˱ǡ�������������������Ů�˷�
վ���Զ��㷢����Ц��һ���������æ��ǰ�к����ˡ���¥�ϴ������������
���ε�������
LONG );
	set("exits", ([
		"west" : __DIR__"wang_8",
	]));

	set("objects", ([
		__DIR__"npc/laobaopo" : 1,
		__DIR__"npc/piaoke" : 1,
		__DIR__"npc/jinv" : 2,
	]));

	setup();
}

