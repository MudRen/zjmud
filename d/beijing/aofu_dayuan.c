inherit ROOM;

void create()
{
	set("short", "������Ժ");
	set("long", @LONG
���߽���Ժ��ӭ����һ����԰����԰�м�ɽˮ�أ��������ۡ���������
һ��޴��ޱȵ���䣬��Ȼ�������չ����ı��ˮ�ص����������˻��ݣ���
���дУ���ľ֦Ҷï�ܣ��ڸ��˴���Ժ�ӣ��Ե���ɭ�ֲ�������һ��������
ľ�Ƴ��ȣ�ͨ�������Ĵ�����
LONG );
	set("exits", ([
		"north" :  __DIR__"aofu_dating",
		"south" :  __DIR__"aofu_zoulang1",
	]));
	set("objects", ([
		__DIR__"npc/yuanding" : 1,
	]));

	setup();
}
