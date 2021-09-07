// Room: /d/gaibang/inhole.c
inherit ROOM;

int do_say(string arg);

void create()
{
	set("short", "�����ڲ�");
	set("long", @LONG
�������ݳ�����㳡���������ڲ���Ҳ��ؤ�����ܵĵ���ͨ�����ܽ�
�㴦�������ﶪ���˸���������������һ�ɳ�����ζ�����������϶���
һ��ǳ���Ŀ��ľ�ơ�
LONG );
	set("exits", ([
		"north" : "d/gaibang/jingji/enter",
		"out" : "d/city/guangchang"
	]));
	set("item_desc",([
		"��ľ�ơ�"	: "���˵������������á�\n"
		ZJOBACTS2"����:say ������·�㲻��ѽ\n",
	]));
	set("objects",([
		CLASS_D("gaibang") + "/zuo-qu" : 1,
	]));
	setup();
}

void init()
{
	add_action("do_say", "say");
}

int do_say(string arg)
{
	if(query("exits/down")) 
	{
		write("���Ѿ��ǿ��ŵ��ˣ�ֱ�ӽ��ɡ�\n");
		return 1;
	}
	else if( arg=="������·�㲻��ѽ" ||  arg=="���������������") 
	{
		write("ֻ����������˵�������Ǳ����ֵܰɣ�������ɡ�\n");
		message("vision", "��������һ��ǽ�������˿�����ԭ���ǵ�Сľ�š�\n", this_player());
		set("exits/down", __DIR__"undertre");
		remove_call_out("close");
		call_out("close", 10, this_object());
		return 1;
	}
	else if(!arg)
		write(INPUTTXT("��˵�����ţ�","say $txt#")+"\n");
	return 0;
}
void close(object room)
{
	message("vision","ֻ��Сľ��ƹ�ع����ˡ�\n", room);
	room->delete("exits/down");
}	
