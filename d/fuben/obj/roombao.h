//roombao.h

//����Ϊ�ر������ͼ
mapping room_place = ([
	"��ɽ"     : "/d/hengshan/",
	"����"	    : "/d/emei/",
	"��ľ��"  : "/d/heimuya/",
	"̩ɽ"     : "/d/taishan/",
	"ѩɽ"     : "/d/xueshan/",
]);
mapping fuben_list = ([
	"heifeng"	:	"�ڷ�կ",
	"canglong" :    "������",
]);
 
object load_room_place(string file_dir)
{
	string *file, bin_dir;
	int max, get_an;

	bin_dir = file_dir;
		
	if (! bin_dir)
		bin_dir = "/binaries" + file_dir;

	if ( file_size(bin_dir) != -2 ) return 0;
	file = list_dirs(bin_dir, -1);

	if ( !(max = sizeof(file)) ) return 0;

	get_an = random(max);

	if ( file_size(bin_dir + file[get_an][0]) <= 0 ) return 0;

	return load_object((file_dir + file[get_an][0])[0..<3]);
}

void do_copy()
{
	object room;
	string *strtemp, locastr, exit;
	int temp, i1, i;
		
	//ȷ��λ�� 
	if (!query("where")) {
		strtemp = keys(room_place);
		i1 = sizeof(strtemp);
		temp = random(i1);
		locastr = room_place[strtemp[temp]];
		room = load_room_place(locastr);
		
		if( objectp(room) )
		{
			exit = room->query("exits"); 
			if ( !room->query("short") 
				|| !mapp(exit) 
				|| !sizeof(exit) 
				|| !room->query("outdoors") 
				|| room->query("no_fight")) 
				destruct(room);
		} 

		if ( !objectp(room) )
			do_copy();
		else {
			set("where", base_name(room));
			set("long", "һ�ű�ע��"+fuben_list[query("fuben_type")]+"���ҵĲر�ͼ��"+
									"����ȥ�������"+strtemp[temp]+"��"+(room->query("short"))+"������\n");
		}
	}
}
