// help.c
#define DEFAULT_LINE 1000

#define DEFAULT_HELP_PATHS ({ "/help/" })

#define DEFAULT_TIT_PATHS ({ "/help/tit/" })

inherit F_CLEAN_UP;

string *tit_search = DEFAULT_TIT_PATHS;
string *help_search = DEFAULT_HELP_PATHS;

int main(object me, string arg)
{
	int i,page;
	string file, *search,str;

	if( !arg )
	{
		if (file_size(HELP_DIR + "/tit/topics") > 0)
		{
			str = replace_string(color_filter(read_file(HELP_DIR+"/tit/topics")),"\n","");
			str = replace_string(str,"$sp#","\n");
			write(ZJOBLONG+str+"\n");
		} else
		{
			write("û���ҵ��������⡣\n");
		}
		return 1;
	}

	seteuid(getuid());

	if(sscanf(arg,"%s %d",arg,page)!=2)
		page = 1;
	if( pointerp(tit_search) ) {
		i = sizeof(tit_search);
		while(i--) if( file_size(tit_search[i] + arg)>0 ) {
			str = replace_string(color_filter(read_file(tit_search[i] + arg)),"\n","");
			str = replace_string(str,"$sp#","\n");
			write(ZJOBLONG+str+"\n");
			return 1;
		}
	}
	if( pointerp(help_search) ) {
		i = sizeof(help_search);
		while(i--) if( file_size(help_search[i] + arg)>0 ) {
			me->zj_more(ZJOBLONG,arg,explode(color_filter(read_file(help_search[i] + arg)),"\n"),DEFAULT_LINE,page);
			return 1;
		}
	}

	if( stringp(file = me->find_command(arg)) ) {
		notify_fail("�����ָ����ڣ����ǲ�û����ϸ��˵���ļ���\n");
		return file->help(me);
	}

	return notify_fail("û��������������˵���ļ���\n");
}

int help(object me)
{
	write(@HELP
ָ���ʽ��help <����>	      ���磺> help cmds
	  help <��������>()	���磺> help call_out()

���ָ���ṩ�����ĳһ�������ϸ˵���ļ������ǲ�ָ�����⣬���ṩ���й�
������ļ���
HELP
	);
	return 1;
}

