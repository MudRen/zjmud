inherit ROOM;

void create()
{
	set("short", "�̳�");
	set("long", @LONG
�����Ǿ��ǵ��̳����ǳ�͢�����շ��ĳ��������ߵ����������������
�����ǿտ����̳�������һ���߸ߵ�ʯ̨��ʯ̨���ɼ���Բľ�������һ��
��ܣ����洹��һ���ֵܴ����������������һ�������εĴ�ľ׮�����滹��
����������Ѫ����
LONG );
       set("exits", ([
		"west" : __DIR__"wang_2",
	]));
	set("objects", ([
		__DIR__"npc/guizishou" : 1,
	]));

	setup();
       set("outdoors", "beijing");
}

