inherit ROOM;

void create()
{
	set("short", "����̨");
	set("long",@LONG
���Ǹ���ͨ��ʯ̨���ഫ������������ٴ�̨������������ȥ���Ǳ�
���صء���Ĳ���á������д��������µ�����֮�������������׾Ͳ���
���С�
LONG );
	set("exits", ([
		"south" : __DIR__"munitang",
		"north" : __DIR__"doushuai",
	]));
	setup();
}

string long()
{
	if (! stringp(query("exits/south")))
		return query("long") + "    ��ֵ��Ǵ��Ž�"
		       "�գ���֪��������ô���¡�\n";

	return query("long");
}
