inherit  ROOM;

void  create  ()
{
	set("short",  "�����");
	set("long",  @LONG
����һ��������ֱ�Ĺٵ�������ݵ���ʮ���ۡ�����ͨ��֬
��֮�������ݣ�������ֱ�ﳤ���ǡ�
LONG);
	set("exits",  ([
		"east"  :  "/d/city/ximenroad",
		"west"  :  __DIR__"hanguguan",
	]));

	set("outdoors", "changan");
	setup();
}

